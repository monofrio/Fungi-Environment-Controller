<?php
include "config.php";
$temp = $_GET['fahrenheit'];
date_default_timezone_set('America/Toronto');
  // Set password. This is just to prevent some random person from inserting values. Must be consistent with YOUR_PASSCODE in Arduino code.
  //if(isset($pass) && ($pass == $passcode)){
  		// If all values are present, insert it into the MySQL database.
  		if(isset($temp)){
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
