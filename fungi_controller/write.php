<?php
include "config.php";
$temp = $_GET['fahrenheit'];
date_default_timezone_set('America/Toronto');
$date= date('m-d-Y H:i:s') ;
  // Set password. This is just to prevent some random person from inserting values. Must be consistent with YOUR_PASSCODE in Arduino code.
  //if(isset($pass) && ($pass == $passcode)){
  		// If all values are present, insert it into the MySQL database.
  		if(isset($temp)){
  			// Create connection.
  			$conn = mysqli_connect($servername, $username, $password, $dbname);
  			if (!$conn) {
  				die("Connection failed: " . mysqli_connect_error());
  			}

  			// Insert values into table. Replace YOUR_TABLE_NAME with your database table name.
  			$sql = "INSERT INTO temp (fahrenheit, tempdate ) VALUES ('$temp','CURDATE()')";
  			if (mysqli_query($conn, $sql)) {
  				echo "OK";
  			} else {
  				echo "Fail: " . $sql . "<br/>" . mysqli_error($conn);
  			}

  			// Close connection.
  			mysqli_close($conn);
  		//}
  	}
  ?>

  <html>
  	<head>
  		<title>Switch Statuses</title>
  		<style>
  		html, body{
  			background-color: #F2F2F2;
  			font-family: Arial;
  			font-size: 1em;
  		}
  		table{
  			border-spacing: 0;
  			border-collapse: collapse;
  			margin: 0 auto;
  		}
  		th{
  			padding: 8px;
  			background-color: #FF837A;
  			border: 1px solid #FF837A;
  		}
  		td{
  			padding: 10px;
  			background-color: #FFF;
  			border: 1px solid #CCC;
  		}

  		div.notes{
  			font-family: arial;
  			text-align: center;
  		}

  		div.current{
  			font-size: 58px;
  			font-family: arial black;
  			text-align: center;
  		}
  		</style>
  	</head>
  	<body>
  		<?php
  			// Database credentials.
        $servername = "markonofriocom.ipagemysql.com";
        $username = "monofrio";
        $password = "F05Df8q1vqRW%F*4yY4L";
        $dbname = "fungi_controller";
  			// Number of entires to display.
  			$display = 15;
  			// Create connection.
  			$conn = mysqli_connect($servername, $username, $password, $dbname);
  			if (!$conn) {
  				die("Connection failed: " . mysqli_connect_error());
  			}

  			// Get the most recent 10 entries.
  			$result = mysqli_query($conn, "SELECT tempdate, fahrenheit FROM temp " . $display . "");
  			while($row = mysqli_fetch_assoc($result)) {
  				echo "<table><tr><th>Date</th><th>Temp</th><th>Date</th></tr>";
  				echo "<tr><td>";
  				echo $row["tempdate"];
  				echo "</td><td>";
  				echo $row["fahrenheit"];
  				echo "</td></tr>";
  				$counter++;
  			}
  			echo "</table>";

  			// Print number of entries in the database. Replace YOUR_TABLE_NAME with your database table name.
  			$row_cnt = mysqli_num_rows(mysqli_query($conn, "SELECT tempdate FROM temp"));
  			echo "<div class='notes'>Displaying last " . $display . " entries.<br/>The database table has " . $row_cnt . " total entries.</div>";

  			// Close connection.
  			mysqli_close($conn);
  		?>
  	</body>
  </html>
