<!DOCTYPE html>
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
  <div style="display:block; float:left;"></div>
<?php
    include 'config.php';
      // Number of entires to display.
      $display = 5;
      $db_tableName = 'temp';

      $result = mysqli_query($conn, "SELECT * FROM ".$db_tableName." ORDER BY date DESC LIMIT " . $display);
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

      // Close connection.
      mysqli_close($conn);
    ?>
</html>
