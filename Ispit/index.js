const express = require('express');
const app = new express();
const path = require('path');
const http = require('http');
const server = http.createServer(app);
const io = require('socket.io').listen(server);

var ind;
const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
var port = new SerialPort('/dev/ttyUSB0', {baudRate: 9600}, function (err) 
{
	if (err) 
	{
		return console.log('Error on create : ', err.message);
	}		
});

const parser = port.pipe(new Readline({ delimiter: '\r\n' }));

port.on('error', function(err) 
{
	console.log('Any Error: ', err.message);
})

parser.on('data', function(data)
{	
    arduino.emit("rezultat",{"komanda" : data})
})

app.use(express.static(path.join(__dirname + '/public')));

var arduino = io.of("/arduino").on('connection', function(socket)
{
	console.log('Arduino user connected');
	
	
	socket.on('disconnect', () => 
	{
		console.log("Arduino user disconnected");
    });``
    
    socket.on('posalji', (ukljuci) =>
    {
        var komanda=ukljuci.komanda;
        console.log(komanda);
        port.write(komanda, function(err)
        {
            if(err)
                console.log("Error ",err.message);
        })
    });


});

server.listen(3000);    
console.log("Express server listening at 3000");
