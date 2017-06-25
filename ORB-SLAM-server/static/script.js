var recordRTC;

function successCallback(stream) {
    var options = {
        mimeType: 'video/webm', // or video/webm\;codecs=h264 or video/webm\;codecs=vp9
        bitsPerSecond: 128000,
    };

    recordRTC = RecordRTC(stream, options);
    recordRTC.startRecording();
}

function errorCallback(error) {
    // maybe another application is using the device
    alert('Failed to get video stream');
}

var mediaConstraints = { video: true, audio: {  facingMode: { exact: "environment" } } };

var running = false;

var baseUrl = 'http://192.168.43.208:5001/';

function start() {
    running = true;
    navigator.mediaDevices.getUserMedia(mediaConstraints).then(successCallback).catch(errorCallback);
}

function upload(formData) {
    fetch(baseUrl + 'upload', {
        method: 'POST',
        body: formData,
    });
}

function stop() {
    running = false;

    recordRTC.stopRecording(function (audioVideoWebMURL) {
        var blob = recordRTC.getBlob();

        var file = new File([blob], 'video.webm', {
            type: 'video/webm',
        });

        var formData = new FormData();
        formData.append('file', file); // upload "File" object rather than a "Blob"
        upload(formData);
    });
}

function checkStatus() {
    fetch(baseUrl + 'status').then(function (res) {
        return res.text();
    }).then(function (text) {
        console.log(text);

        if (text == 'ON') {
            console.log('Starting', running);
            if (!running) {
                start();
            }
        } else {
            if (running) {
                stop();
            }
        }
    });
}

setInterval(checkStatus, 1000);
