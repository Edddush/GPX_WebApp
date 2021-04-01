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
  
      if (names.length >= 2) { 
        $(".scroll").css("height", "330px"); 
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
      let r_names = data.Rname;
      let r_loop = data.Risloop;
      let r_points = data.Rwpts;
      let r_lens = data.Rlens;

      let t_type = data.Tcurrent;
      let t_names = data.Tnames;
      let t_loop = data.Tisloop;
      let t_points = data.Twpts;
      let t_lens = data.Tlens;
      
      // console.log(r_names);
      // console.log(t_names);

    //   for(let i in r_names){
    //     let theRows = "<tr>";
    //     theRows += "<td style= 'width: 80px; text-align: center;'>" + r_type[i] + "</td>";
    //     theRows += "<td style= 'width: 40px; text-align: center;'>" + r_names[i] + "</td>";        
    //     theRows += "<td style= 'width: 80px; text-align: center;'>" + r_points[i] + "</td>";
    //     theRows += "<td style= 'width: 40px; text-align: center;'>" + r_lens[i] + "</td>";
    //     theRows += "<td style= 'width: 40px; text-align: center;'>" + r_loop[i] + "</td>";
    //     theRows += "</tr>";
    //     $("#routes").append(theRows);
    //   }
    
    //   for(let i in t_names){
    //     let theRows = "<tr>";
    //     theRows += "<td style= 'text-align: center;'>" + t_type[i] + "</td>";
    //     theRows += "<td style= 'text-align: center;'>" + t_names[i] + "</td>";        
    //     theRows += "<td style= 'text-align: center;'>" + t_points[i] + "</td>";
    //     theRows += "<td style= 'text-align: center;'>" + t_lens[i] + "</td>";
    //     theRows += "<td style= 'text-align: center;'>" + t_loop[i] + "</td>";
    //     theRows += "</tr>";
    //     $("#routes").append(theRows);
    //   }
    }, fail: function (error) {
      console.log(error);
    },
  });
}