<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="shortcut icon" href="https://www.markonofrio.com/images/favicon.png">
    <title>Temp Statuses</title>
  <link href='style.css' rel="stylesheet" type="text/css" />
  </head>
  <body>
    <style>

  body {
    font: 10px sans-serif;
  }

  .axis line,
  .axis path {
    fill: none;
    stroke: #000;
    shape-rendering: crispEdges;
  }

  .arrow {
    stroke: #000;
    stroke-width: 1.5px;
  }

  .outer,
  .inner {
    shape-rendering: crispEdges;
  }

  .outer {
    fill: none;
    stroke: #000;
  }

  .inner {
    fill: #ccc;
    stroke: #000;
    stroke-dasharray: 3, 4;
  }

  </style>



    <?php
      include 'config.php';
      // Number of entires to display.
      $display = 5;
      $db_tableName = 'temp';
      // Create connection.
      $conn = mysqli_connect($servername, $username, $password, $dbname);
      if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
      }
      // Get the most recent 10 entries.
      $result = mysqli_query($conn, "SELECT * FROM ".$db_tableName." ORDER BY 'date' DESC LIMIT " . $display);
      $query  = mysqli_query($conn, "SELECT 'fahrenheit', 'date',  FROM ".$db_tableName."");

      $row_cnt = mysqli_num_rows(mysqli_query($conn, "SELECT 'fahrenheit' FROM ".$db_tableName.""));

      while($row = mysqli_fetch_assoc($result)) {
        echo "<table><tr><th>Date</th><th>Fahrenheit</th></tr>";
        echo "<tr><td>";
        echo $row["date"];
        echo "</td><td>";
        echo $row["fahrenheit"];
        echo " </td></tr>";
        $counter++;
      }
      echo "</table>";

      // Print number of entries in the database. Replace YOUR_TABLE_NAME with your database table name.
      echo "<div class='notes'>Displaying last " . $display . " entries.<br/>The database table has " . $row_cnt . " total entries.</div>";


      $data = array();
      for ($x = 0; $x < $row_cnt; $x++) {
              // $data[] = mysqli_fetch_assoc($result);
               $data[] = $result->fetch_all(MYSQLI_ASSOC);
          }
      echo "json data: </br>";
      echo json_encode($data);

      // Close connection.
      mysqli_close($conn);
    ?>
    <div><?php echo $date; ?></div>
<!--

    <script src="//d3js.org/d3.v3.min.js"></script>
    <script>

            var margin = {top: 20, right: 20, bottom: 20, left: 20},
                padding = {top: 60, right: 60, bottom: 60, left: 60},
                outerWidth = 960,
                outerHeight = 500,
                innerWidth = outerWidth - margin.left - margin.right,
                innerHeight = outerHeight - margin.top - margin.bottom,
                width = innerWidth - padding.left - padding.right,
                height = innerHeight - padding.top - padding.bottom;

            var x = d3.scale.identity()
                .domain([0, width]);

            var y = d3.scale.identity()
                .domain([0, height]);

            var xAxis = d3.svg.axis()
                .scale(x)
                .orient("bottom");

            var yAxis = d3.svg.axis()
                .scale(y)
                .orient("right");

            var svg = d3.select("body").append("svg")
                .attr("width", outerWidth)
                .attr("height", outerHeight)
              .append("g")
                .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

            var defs = svg.append("defs");

            defs.append("marker")
                .attr("id", "triangle-start")
                .attr("viewBox", "0 0 10 10")
                .attr("refX", 10)
                .attr("refY", 5)
                .attr("markerWidth", -6)
                .attr("markerHeight", 6)
                .attr("orient", "auto")
              .append("path")
                .attr("d", "M 0 0 L 10 5 L 0 10 z");

            defs.append("marker")
                .attr("id", "triangle-end")
                .attr("viewBox", "0 0 10 10")
                .attr("refX", 10)
                .attr("refY", 5)
                .attr("markerWidth", 6)
                .attr("markerHeight", 6)
                .attr("orient", "auto")
              .append("path")
                .attr("d", "M 0 0 L 10 5 L 0 10 z");

            svg.append("rect")
                .attr("class", "outer")
                .attr("width", innerWidth)
                .attr("height", innerHeight);

            var g = svg.append("g")
                .attr("transform", "translate(" + padding.left + "," + padding.top + ")");

            g.append("rect")
                .attr("class", "inner")
                .attr("width", width)
                .attr("height", height);

            g.append("g")
                .attr("class", "x axis")
                .attr("transform", "translate(0," + height + ")")
                .call(xAxis);

            g.append("g")
                .attr("class", "y axis")
                .attr("transform", "translate(" + width + ",0)")
                .call(yAxis);

            svg.append("line")
                .attr("class", "arrow")
                .attr("x2", padding.left)
                .attr("y2", padding.top)
                .attr("marker-end", "url(#triangle-end)");

            svg.append("line")
                .attr("class", "arrow")
                .attr("x1", innerWidth / 2)
                .attr("x2", innerWidth / 2)
                .attr("y2", padding.top)
                .attr("marker-end", "url(#triangle-end)");

            svg.append("line")
                .attr("class", "arrow")
                .attr("x1", innerWidth / 2)
                .attr("x2", innerWidth / 2)
                .attr("y1", innerHeight - padding.bottom)
                .attr("y2", innerHeight)
                .attr("marker-start", "url(#triangle-start)");

            svg.append("line")
                .attr("class", "arrow")
                .attr("x2", padding.left)
                .attr("y1", innerHeight / 2)
                .attr("y2", innerHeight / 2)
                .attr("marker-end", "url(#triangle-end)");

            svg.append("line")
                .attr("class", "arrow")
                .attr("x1", innerWidth)
                .attr("x2", innerWidth - padding.right)
                .attr("y1", innerHeight / 2)
                .attr("y2", innerHeight / 2)
                .attr("marker-end", "url(#triangle-end)");

            svg.append("text")
                .text("origin")
                .attr("y", -8);

            svg.append("circle")
                .attr("class", "origin")
                .attr("r", 4.5);

            g.append("text")
                .text("translate(margin.left, margin.top)")
                .attr("y", -8);

    </script> -->

  </body>
</html>
