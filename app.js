'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)

const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');
const lib = require('express-fileupload');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }

  let uploadFile = req.files.uploadFile;

  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******************** Your code goes here ********************
const bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: true }));

let library = ffi.Library("./libgpxparser.so", {
  'validGPXJSON': ["string", ["string", "string"]],
  'validGPX' : ["int", ["string", "string"]],
  'routes' : ["string", ["string"]],
  'tracks' : ["string", ["string"]],
  'newGpx' : ["int", ["string", "string"]],
  'newRoute' :["int", ["string", "string"]]
});

function checkExtension(file) {
  if (file.slice(file.length - 3, file.length) !== "gpx") {
    return false;
  }
  return true;
}

app.get("/retrieveFiles", function(err, res){
  const arrayOfFiles = [];
  const version = [];
  const creator = [];
  const rte = [];
  const trk = [];
  const wpt = [];
  
  fs.readdir("uploads/", (err, files) => {
    files.forEach((readFile) => {
      let json = library.validGPXJSON("uploads/" + readFile, "gpx.xsd");

      if(checkExtension("uploads/" + readFile) && json != "{}"){
        arrayOfFiles.push(readFile);
        version.push(JSON.parse(json).version);
        creator.push(JSON.parse(json).creator);
        rte.push(JSON.parse(json).numRoutes);
        trk.push(JSON.parse(json).numTracks);
        wpt.push(JSON.parse(json).numWaypoints);
      } 
    });
    res.send({
      names: arrayOfFiles,
      vers: version,
      crea: creator,
      routes: rte,
      tracks: trk,
      points: wpt,
    });
  });
});


app.get("/changeV", function(req, res){
  const Rtype = [];
  const Rname = [];
  const Rloop = [];
  const Rpoints = [];
  const Rlength = [];

  const Ttype = [];
  const Tname = [];
  const Tloop = [];
  const Tpoints = [];
  const Tlength = [];
  
  let Rjson = JSON.parse(library.routes("uploads/" + req.query.fileName));
  
  if(Rjson !== '[]'){
    for (var i=0; i < Rjson.length; i++) {
      Rname.push(Rjson[i].name);
      Rloop.push(Rjson[i].loop);
      Rlength.push(Rjson[i].len);
      Rpoints.push(Rjson[i].numPoints);
      var index = parseInt(i) + 1;
      Rtype.push("Route " + index);
    }
  }

  let Tjson = JSON.parse(library.tracks("uploads/" + req.query.fileName));

  if(Tjson !== '[]'){
    for (var i = 0; i < Tjson.length; i++) {
      Tname.push(Tjson[i].name);
      Tloop.push(Tjson[i].loop);
      Tlength.push(Tjson[i].len);
      Tpoints.push(Tjson[i].points);
      var index = parseInt(i) + 1;
      Ttype.push("Track " + index);
    }
  }

  res.send({
    Rcurrent : Rtype,
    Rnames : Rname,
    Risloop: Rloop,
    Rwpts: Rpoints,
    Rlens: Rlength,

    Tcurrent : Ttype,
    Tnames : Tname,
    Tisloop: Tloop,
    Twpts: Tpoints,
    Tlens: Tlength,
  });
});


app.get("/validate", function (req, res){
  let valid = library.validGPX("uploads/" + req.query.fileName, "gpx.xsd");
  if(valid == 0){
    console.log("Invalid gpx");
  } else{
    console.log("Valid gpx");
  }
  
  res.send({
    obtain: valid,
  });
});

app.post('/removeFromServer', function(req, res){
  let pop = req.body.toDelete;
  fs.unlink('uploads/'+ pop, function(err){
    if(err) {
      throw err;
    }
  })
  res.send({
    message: "File "+ req.body.toDelete + " has been removed from server",
  });
});

app.post("/creategpx", (req, res)=>{
  let input = req.body.naming;
  library.newGpx("uploads/" + input, "gpx.xsd");
  res.send("Created a New GPX");
});

app.post("/newRoute", (req, res)=>{
  library.newRoute("uploads/" + req.body.inputFile, req.body.wpt);
  res.send("Created a new Route");
});



app.listen(portNum);
console.log('Running app at localhost: ' + portNum);
