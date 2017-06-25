import time
import os
from flask import Flask, request, jsonify, render_template
from flask_cors import CORS, cross_origin


app = Flask(__name__, static_url_path='/static')
status = "OFF"
CORS(app)


@app.route('/')
def admin():
    return render_template("admin.html")


@app.route('/upload', methods=['POST'])
def upload():
    file = request.files['file']

    filename = str(time.time())

    directory = 'uploads/{}'.format(filename)
    os.mkdir(directory)

    video_file = os.path.join(directory, filename)
    file.save(video_file)

    orb_directory = '{}/rgb'.format(directory)
    os.mkdir(orb_directory)

    os.system("ffmpeg -i {} -vf fps=5 {}/rgb/thumb%04d.jpg -hide_banner".format(video_file, directory))

    with open(os.path.join(directory, 'rgb.txt'), 'a') as f:

        arr = list(os.listdir(orb_directory))
        arr.sort()
        ts = time.time()
        i = 0

        for a in arr:
            tsnow = ts + (1/5 * i)
            i += 1
            f.write('{} rgb/{}\n'.format(str(tsnow), a))

    return 'OK'


@app.route('/start')
def start():
    global status
    status = "ON"
    return status


@app.route('/stop')
def stop():
    global status
    status = "OFF"
    return status


@app.route('/status')
def get_status():
    return status


app.run(host='0.0.0.0', port=5001, debug=True)
