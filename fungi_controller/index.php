<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="shortcut icon" href="https://www.markonofrio.com/images/favicon.png">
    <title>Temp Statuses</title>

    <link href='style.css' rel="stylesheet" type="text/css" />
    <script src="d3.v4.min.js"></script>

  </head>
  <body>
  <script>
      // Sample Data: {"date":"2017-12-03 01:26:31","fahrenheit":"71"}
      // Formated Data:  { "date": "03-Dec-17", "fahrenheit": "71"}
      d3.select("body").append("h1").text("Temp Chart");
      d3.select("body").append("div").attr("class", "stats");
      d3.select("body").append('svg').attr("width", "500").attr("height", "300");

      var svg = d3.select("svg"),
          margin = {top: 20, right: 20, bottom: 30, left: 50},
          width = +svg.attr("width") - margin.left - margin.right,
          height = +svg.attr("height") - margin.top - margin.bottom,
          g = svg.append("g").attr("transform", "translate(" + margin.left + "," + margin.top + ")");

      var x = d3.scaleTime()
          .rangeRound([0, width]);

      var y = d3.scaleLinear()
          .rangeRound([height, 0]);

      d3.json('http://esp8266.markonofrio.com/fungi_controller/data.php',
          function(error, d) {
              if (error) return console.warn(error);

              var rows = d.length;
              console.log("Number of records: ",rows);

              var sumOfTemp = [];
              var numberOfRecords = 360;

              for(var i = 0; i < numberOfRecords; i++){
                  sumOfTemp.push(d[i].fahrenheit);
              }
              var tempSum = d3.sum(sumOfTemp),
                  averageTemp = (tempSum / numberOfRecords).toFixed(2),
                  maxTemp = d3.max(sumOfTemp),
                  minTemp = d3.min(sumOfTemp);
              // Fahrenheit Data Log
              console.log("Sum of last 30 Temps: ", tempSum);
              console.log("Average Temp: ", averageTemp);
              console.log("Max Temp: ", maxTemp);
              console.log("Min Temp: ", minTemp);

              var stats = d3.selectAll(".stats").append("th").text("Fahrenheit Data Log for the last " + (numberOfRecords * 10 / 60 ) + " minutes");
                  // .append("tr")
                  //   .append("td")
                  //   .text("Time :");
                  //   // .text(d[0].date);
              //
              // stats.append("tr");
              // stats.append("td").text("Max Temp: ");
              // stats.append("td").text(maxTemp);
              //
              // stats.append("tr");
              // stats.append("td").text("Min Temp: ");
              // stats.append("td").text(minTemp);
              //
              // stats.append("tr");
              // stats.append("td").text("Avarage Temp: ");
              // stats.append("td").text(averageTemp);

          });
  </script>
  <div style="display:block; float:left;"></div>
<?php
//    include 'config.php';
//      // Number of entires to display.
//      $display = 5;
//      $db_tableName = 'temp';
//
//      $result = mysqli_query($conn, "SELECT * FROM ".$db_tableName." ORDER BY date DESC LIMIT " . $display);
//      $row_cnt = mysqli_num_rows(mysqli_query($conn, "SELECT 'fahrenheit' FROM ".$db_tableName.""));
//
//      while($row = mysqli_fetch_assoc($result)) {
//        echo "<table><tr><th>Date</th><th>Fahrenheit</th></tr>";
//        echo "<tr><td>";
//        echo $row["date"];
//        echo "</td><td>";
//        echo $row["fahrenheit"];
//        echo " </td></tr>";
//        $counter++;
//      }
//      echo "</table>";
//
//      // Print number of entries in the database. Replace YOUR_TABLE_NAME with your database table name.
//      echo "<div class='notes'>Displaying last " . $display . " entries.<br/>The database table has " . $row_cnt . " total entries.</div>";
//
//      // Close connection.
//      mysqli_close($conn);
//    ?>

</html>
