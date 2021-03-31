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
let library = ffi.Library("./libgpxparser.so", {
  createGPXdoc: ["pointer", ["string"]]
  // GPXtoJSON: ["string", ["pointer"]],
});


function validateExt(file) {
  if (file.slice(file.length - 3, file.length) !== "gpx") {
    return false;
  }
  return true;
}

let descJSON = sharedLib.GPXtoJSON();
let doc = library.createGPXdoc(file.name);
let descJSON = library.GPXtoJSON(doc);
let family = JSON.parse(descJSON);


//Iterate through the array for-of loop
console.log("\n\nUsing for-of loop\n");
let gen = 1;

for (let generation of family){
	console.log("Generation "+ gen);

	for (let ind of generation){
		//Let JavaScript display the object using its default string representation
		console.log(ind);

		//Display instance variables of the object
		console.log("Given name: "+ind.name);
		// console.log("Surname: "+ind.surname);

	}
	gen += 1;
}

//Sample endpoint
app.get('/end1', function(req , res){
  let retStr = req.query.data1 + " " + req.query.data2;
  res.send(
    {
      somethingElse: retStr
    }
  );
});


console.log("ffiTest.js: sharedLib.getDesc() returned "+descJSON+"\n");

app.listen(portNum);
console.log('Running app at localhost: ' + portNum);
