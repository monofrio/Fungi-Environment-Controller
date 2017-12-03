<?php
// Set password. This is just to prevent some random person from inserting values.
// Must be consistent with YOUR_PASSCODE in Arduino code.
$passcode = "";

$servername = "";
$username = "";
$password = "";
$dbname = "";

// Create connection.
$conn = mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}
