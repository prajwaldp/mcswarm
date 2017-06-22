import gym
import numpy as np
import matplotlib.pyplot as plt
from sklearn.pipeline import FeatureUnion
from sklearn.preprocessing import StandardScaler
from sklearn.kernel_approximation import RBFSampler
from sklearn.linear_model import SGDRegressor
import pickle
from argparse import ArgumentParser


class FeatureTransformer:

    def __init__(self, env):

        observation_examples = np.array(
            [env.observation_space.sample() for x in range(10000)])
        scaler = StandardScaler()
        scaler.fit(observation_examples)

        featurizer = FeatureUnion([
            ("rbf1", RBFSampler(gamma=5.0, n_components=500)),
            ("rbf2", RBFSampler(gamma=2.0, n_components=500)),
            ("rbf3", RBFSampler(gamma=1.0, n_components=500)),
            ("rbf4", RBFSampler(gamma=0.5, n_components=500))
        ])

        example_features = featurizer.fit_transform(
            scaler.transform(observation_examples))

        self.dimensions = example_features.shape[1]
        self.scaler = scaler
        self.featurizer = featurizer


    def transform(self, observations):

        scaled = self.scaler.transform(observations)
        return self.featurizer.transform(scaled)


class Model:

    def __init__(self, env, feature_transformer):

        self.env = env
        self.models = []
        self.feature_transformer = feature_transformer

        for i in range(env.action_space.n):

            model = SGDRegressor(learning_rate='constant')
            model.partial_fit(
                feature_transformer.transform([env.reset()]), [0])
            self.models.append(model)


    def predict(self, s):

        X = self.feature_transformer.transform([s])
        assert(len(X.shape) == 2)
        return np.array([m.predict(X)[0] for m in self.models])


    def update(self, s, a, G):

        X = self.feature_transformer.transform([s])
        assert(len(X.shape) == 2)
        self.models[a].partial_fit(X, [G])


    def sample_action(self, s, eps):

        if np.random.random() < eps:
            return self.env.action_space.sample()
        else:
            return np.argmax(self.predict(s))


def run_episode(model, eps, gamma):

    observation = env.reset()
    done = False
    totalreward = 0
    iters = 0

    while not done and iters < 10000:

        action = model.sample_action(observation, eps)
        prev_observation = observation
        observation, reward, done, info = env.step(action)

        if args.render:
            env.render()

        # update the model
        G = reward + gamma * np.max(model.predict(observation)[0])
        model.update(prev_observation, action, G)

        totalreward += reward
        iters += 1

    return totalreward


def plot_running_avg(totalrewards):

    N = len(totalrewards)
    running_avg = np.empty(N)

    for t in range(N):
        running_avg[t] = totalrewards[max(0, t - 100):(t + 1)].mean()

    plt.plot(running_avg)
    plt.title("Running Average")
    plt.show()


if __name__ == '__main__':

    parser = ArgumentParser()
    parser.add_argument('-n', help='number of episodes', default=300)
    parser.add_argument('-r', '--render', help='render',
                        action='store_true')
    parser.add_argument('-l', '--load', help='load model from file',
                        action='store_true')
    args = parser.parse_args()


    env = gym.make('MountainCar-v0')
    ft = FeatureTransformer(env)


    if args.load:
        print('Loading previous model from file')

        with open('model', 'rb') as f:
            model = pickle.load(f)

    else:
        print('Building a new model')
        model = Model(env, ft)


    gamma = 0.99

    N = int(args.n)
    totalrewards = np.empty(N)

    for n in range(N):
        eps = 0.05 * (0.96**n)
        totalreward = run_episode(model, eps, gamma)
        totalrewards[n] = totalreward
        print("episode:", n, "total reward:", totalreward)

    print("avg reward for last 100 episodes:", totalrewards[-100:].mean())
    print("total steps:", -totalrewards.sum())

    plt.plot(totalrewards)
    plt.title("Rewards")
    plt.show()

    plot_running_avg(totalrewards)

    with open('model', 'wb') as f:
        pickle.dump(model, f)

    env.close()
