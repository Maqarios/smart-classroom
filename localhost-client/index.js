const SerialPort = require('serialport');
const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const localtunnel = require('localtunnel');
const arduinoPort = new SerialPort('/dev/ttyACM0', { baudRate: 9600 });
const port = 8080;
const app = express();
app.use(cors());
// support parsing of application/json type post data
app.use(bodyParser.json());
//support parsing of application/x-www-form-urlencoded post data
app.use(bodyParser.urlencoded({ extended: true }));
app.get('/', (req,res) =>{
    res.send('hey idiot');
});
app.post('/exam', (req, res) => {
    if (!req.body){
        return res.status(422).send({
            err: 'failed to find time data'
        });
    }
    if (!req.body.name) {
        return res.status(422).send({
            err: 'no user supplied'
        });
    }
    if (!req.body.password) {
        return res.status(422).send({
            err: 'no password supplied'
        })
    }
    if (!req.body.startTime) {
        return res.status(422).send({
            err: 'start time was not supplied'
        });
    }
    if (!req.body.hours || isNaN(req.body.hours)) {
        return res.status(422).send({
            err: 'duration hours are invalid'
        });
    }
    if (!req.body.minutes || isNaN(req.body.minutes)) {
        return res.status(422).send({
            err: 'duration minutes are invalid'
        });
    }
    arduinoPort.write(
        `startTime: ${req.body.startTime} // durationHours: ${req.body.hours} // durationMinutes: ${req.body.minutes} // durationSeconds: ${req.body.seconds} \r\n`,
        (err) => {
            console.log(err.message);
        }
    );
    res.status(200).send({
        err: null,
        msg: 'successfully sent data to arduino'
    });
});

const tunnel = localtunnel(
    8080,
    { subdomain: 'embedded-smart-classroom-2019' },
    (err, tunnel) => {
        if (err) {
            return console.log(err);
        }
        console.log(tunnel.url);
    });
app.listen(port, () => {
    console.log(`server is listening on port ${port}`);
});