<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="shortcut icon" href="https://www.markonofrio.com/images/favicon.png">
    <title>Temp Data Statuses</title>
  </head>
  <body>
    <?php
    include 'config.php';
      $db_tableName = 'temp'; //UPDATE TABLE NAME
      $sql = "SELECT * FROM temp";

      $result = $dbh->query($sql)->fetchAll(PDO::FETCH_ASSOC);

      $return = [];
      foreach ($result as $row) {
          $return[] = [
                'date' => $row['date'],
                'fahrenheit' => $row['fahrenheit']
              ];
      }
      //header('Content-type:application/json;charset=utf-8');
      header("Access-Control-Allow-Origin: *");
      echo json_encode($return);

      // Close connection.
      mysqli_close($conn);
 ?>
</body>
</html>
