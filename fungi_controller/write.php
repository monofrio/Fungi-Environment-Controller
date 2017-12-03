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
  			$sql = "INSERT INTO temp (fahrenheit) VALUES ('$temp')";
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
