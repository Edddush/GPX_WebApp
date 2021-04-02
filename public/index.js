// // Put all onload AJAX calls here, and event listeners
// jQuery(document).ready(function() {
//     // On page-load AJAX Example
//     jQuery.ajax({
//         type: 'get',            //Request type
//         dataType: 'json',       //Data type - we will use JSON for almost everything
//         url: '/endpoint1',   //The server endpoint we are connecting to
//         data: {
//             data1: "Value 1",
//             data2:1234.56
//         },
//         success: function (data) {
//             /*  Do something with returned object
//                 Note that what we get is an object, not a string,
//                 so we do not need to parse it on the server.
//                 JavaScript really does handle JSONs seamlessly
//             */
//             jQuery('#blah').html("On page load, received string '"+data.somethingElse+"' from server");
//             //We write the object to the console to show that the request was successful
//             console.log(data);
//
//         },
//         fail: function(error) {
//             // Non-200 return, do something with error
//             $('#blah').html("On page load, received error from server");
//             console.log(error);
//         }
//     });
//
//     // Event listener form example , we can use this instead explicitly listening for events
//     // No redirects if possible
//     $('#someform').submit(function(e){
//         $('#blah').html("Form has data: "+$('#entryBox').val());
//         e.preventDefault();
//         //Pass data to the Ajax call, so it gets passed to the server
//         $.ajax({
//             //Create an object for connecting to another waypoint
//         });
//     });
// });

jQuery(document).ready(function(){
  getFileLog();
  uploadFile();
  createFile();
  current();
});


// Populate first table
function getFileLog(){
  $.ajax({
    type: "get",
    datatype: "json",
    url: "/retrieveFiles",

    success: function(data){
      let names = data.names
      let rtes = data.routes
      let trks = data.tracks
      let wpts = data.points
      let version = data.vers
      let creator = data.crea

      if (names.length === 0) {
        $("#filelogTable").append( "<h3 style= 'text-align: center'> No Files </h3>");
      }
  
      if (names.length > 2) { 
        $(".scroll").css("height", "330px");
        // $(".scroll").css("width", "600px"); 
      }
  
      for(let i in names) {
        let theRows = "<tr>";
        theRows += "<td style= 'width: 80px; text-align: center;' > <a href=" + names[i] + ' download ">' + names[i] + "</a></td>";
        theRows += "<td style= 'width: 40px; text-align: center;'>" + version[i] + "</td>";        
        theRows += "<td style= 'width: 80px; text-align: center;'>" + creator[i] + "</td>";
        theRows += "<td style= 'width: 40px; text-align: center;'>" + wpts[i] + "</td>";
        theRows += "<td style= 'width: 40px; text-align: center;'>" + rtes[i] + "</td>";
        theRows += "<td style= 'width: 40px; text-align: center;'>" + trks[i] + "</td>";
        theRows += "</tr>";

        $("#files").append(theRows);
        let dropdown = `<button class='dropdown-item dropdown'>` + names[i] + "</button>";
        $("#dropdown").append(dropdown);
        let available = `<option>` + names[i] + "</option>";
        $("#newRoute").append(available);
      }

      $("button.dropdown").click(function () {
        updateTable($(this)[0].innerHTML);
      });
    },
    error: function (error) {
      console.log(error);
    },
  });    
}

function updateTable(nameOfFile){ 
  $("#GPXviewPanel")[0].innerHTML = nameOfFile;
  
  $.ajax({
    type: "get",
    url: "/changeV",
    datatype: "json",
    data: {fileName : nameOfFile},
    
    success: function(data){
      
      if($("#routes").children().length > 0){
        $("#routes").children().empty();
      }
      
      let r_type = data.Rcurrent;
      let r_names = data.Rnames;
      let r_loop = data.Risloop;
      let r_points = data.Rwpts;
      let r_lens = data.Rlens;

      let t_type = data.Tcurrent;
      let t_names = data.Tnames;
      let t_loop = data.Tisloop;
      let t_points = data.Twpts;
      let t_lens = data.Tlens;

      for(let i in r_names){
        let rename = "";
        let otherData = "";
        let theRows = "<tr>";
        theRows += "<td style= ' text-align: center;'>" + r_type[i] + "</td>";
        theRows += "<td style= ' text-align: center;'>" + r_names[i] + "</td>";        
        theRows += "<td style= ' text-align: center;'>" + r_points[i] + "</td>";
        theRows += "<td style= ' text-align: center;'>" + r_lens[i] + "</td>";
        theRows += "<td style= ' text-align: center;'>" + r_loop[i] + "</td>";
        theRows +=  "<td style= ' text-align: center;'>" ;

        rename += "<button 'type= button class=btn btn-secondary btn-sm'>"+ "Rename </button>";
        theRows += rename;
        otherData += "<button 'type= button  class= btn btn-info btn-sm  data-dismiss= modal'>" + "Show Other Data</button>";
        theRows += otherData;
        theRows += "</td>"
        theRows += "</tr>";
        $("#routes").append(theRows);

        $("button.rename").click(function () {
          rename(r_names[i]);
        });
      }
    
      for(let i in t_names){
        let theRows = "<tr>";
        theRows += "<td style= 'text-align: center;'>" + t_type[i] + "</td>";
        theRows += "<td style= 'text-align: center;'>" + t_names[i] + "</td>";        
        theRows += "<td style= 'text-align: center;'>" + t_points[i] + "</td>";
        theRows += "<td style= 'text-align: center;'>" + t_lens[i] + "</td>";
        theRows += "<td style= 'text-align: center;'>" + t_loop[i] + "</td>";
        theRows +=  "<td style= ' text-align: center;'>" 
        theRows += "<button 'type= button class=btn btn-secondary btn-sm'>"+ 'Rename' + "</button>";
        theRows += "<button 'type= button class= btn btn-info btn-sm  data-dismiss= modal'>" + "Show Other Data</button>";
        theRows += "</td>"
        theRows += "</tr>";
        $("#routes").append(theRows);
      }
    }, fail: function (error) {
      console.log(error);
    },
  });
}

function uploadFile(){
  //     // Event listener form example , we can use this instead explicitly listening for events
//     // No redirects if possible
  $('#uploadForm').submit(function(event){
      event.preventDefault();

      if($("#selectFile")[0].value.length > 0){
        let selectFile = $("#selectFile")[0].files[0];
        console.log(selectFile.name + " waiting validation ");
        let files = new FormData();
        files.append("uploadFile", selectFile);
        // for (var p of files) {
        //   console.log(p);
        // }
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
          type: "post",
          url: "/upload",
          data: files,
          contentType: false,
          processData: false,
          success: function(){     
            $.ajax({
              type: "get",
              url: "/validate",
              data: {fileName: selectFile.name},
              datatype: "json",
              success: function(data){
                if(data.obtain === 1){
                  alert(selectFile.name + " ready to use");
                  location.reload();
                } else{
                  alert(selectFile.name + " is invalid (check gpx extension and format)");
                  $.ajax({
                    type: "post",
                    url: "/removeFromServer",
                    data: { toDelete: selectFile.name},
                    success: function(data){
                      console.log(data.message);
                    },
                    fail: function(error){
                      console.log(error);
                    }
                  });
                }
              }
            });
          },
          fail: function(error){ 
            alert(selectFile.name + "cannot upload");
            console.log(error);
          } 
        //Create an object for connecting to another waypoint
        });
      } else{
        alert("Choose a file to proceed");
      }
  });
}

function createFile(){
    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#fileInput').submit(function(event){
        event.preventDefault();
       
        if($("#userFileName")[0].value.length > 0){
          let input = $("#userFileName")[0].value;
          //Pass data to the Ajax call, so it gets passed to the server
          // console.log(input);
          $.ajax({
            type: "post",
            url: "/creategpx",
            datatype: "json",
            data:{naming :  $("#userFileName")[0].value + ".gpx"},
            success: function(){
              alert("File " + input + ".gpx has been uploaded");
              location.reload();
            }, fail: function(){
              alert("The file could not be uploaded, try again.");
            }
          //Create an object for connecting to another waypoint
          });
        } else{
          alert("Please fill out the required fields: filename");
        }
    });
}

function current(){
  $("#submitRoute").click(function(event){
    let nameOfFile = $("#newRoute")[0].selectedOptions[0].innerHTML;
    let info = "{";
    let long = $(`#lon`);
    let lati = $(`#lat`);

    if(long[0].value < 180 && long[0].value > -180
      && lati[0].value < 90 && lati[0].value > -90 ){
        info += "lat:" + lati[0].value;
        info += ",lon:" + long[0].value;
        info += "}";

        $.ajax({
          type:"post",
          datatype:"json",
          url: "/newRoute",
          data: {inputFile : nameOfFile, wpt: info},
          success: function(){
            location.reload();
          }, fail: function(){
            alert("Failed to add the route");
          },
        });
    } else{
      alert("values out of range -/+180 lon -/+90 lat");
    }
  });
}

function rename(name){
  console.log(name);

  // $.ajax({
  //   type: "post",
  //   url: "/newName",
  //   data: {inputFile : nameOfFile, name},
  //   success: function(){
  //     location.reload();
  //   }, fail: function(){
  //     alert("rename failed");
  //   },
  // });
}

$("#find").click(function (event) {
  event.preventDefault();
  // var lats = $("#lonstart")[0].value;
  // var late = $("#latstart")[0].value;
  // var lons = $("#lonend")[0].value;
  // var lone = $("#latend")[0].value;
  // var delta = $("#delta")[0].value;
    for (let i = 0; i < 3; i++) {
      let theRows = "<tr>";
      theRows += "<td>" + "route " + (i + 1) + "</td>";
      theRows += "<td>" + "Some route" + "</td>";
      theRows += "<td>" + "5" + "</td>";
      theRows += "<td>" + "300"+ "</td>";
      theRows += "<td>" + "true"+ "</td>";
      // let otherD = `<button type='button' class='btn btn-secondary'`
      theRows += "</tr>";
      $("#paths").append(theRows);
    }
});