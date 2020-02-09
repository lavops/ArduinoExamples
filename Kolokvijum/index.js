const express=require('express');
const app=new express();
const http=require('http');
const path = require('path');
const server=http.createServer(app);
const io=require('socket.io').listen(server);
const SerialPort=require('serialport');
var indikator;
const Readline=SerialPort.parsers.Readline;
var port=new SerialPort('/dev/ttyUSB0',{baudRate:9600},function(err){
    if(err){
        return console.log("Greskaa kod porta",err.message);
    }
});
const parser=port.pipe(new Readline({delimiter:'\r\n'}));

port.on('error',function(err){
    console.log("Greskaaa: ",err.message);
});

parser.on('data',function(data){
    console.log(data);
    var msg ={"temp1":data.split(" ")[0],"temp2":data.split(" ")[1]}
    socket.emit('obrada',msg);

});

app.use(express.static(path.join(__dirname + '/public')));

var socket=io.of('/arduino').on('connection',function(soket){
    console.log("Connected");
    soket.on('disconnect',()=>{
        console.log("Disconnected");
    });
});


server.listen(3000);  

