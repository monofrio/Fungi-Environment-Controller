<?php
    include 'config.php';
      $db_tableName = 'temp'; //UPDATE TABLE NAME
      $sql = 'SELECT * FROM temp';

      $result = $dbh->query($sql)->fetchAll(PDO::FETCH_ASSOC);

      $return = [];
      foreach ($result as $row) {

//**    SAMPLE DATA: {"date": "2017-12-03 01:26:31", "fahrenheit": "71"}
//**    DATE FORMAT: 24-Apr-07
          $time = strtotime($row['date']);
          $myFormatForView = date('d-M-y H:i:s', $time);

          $return[] = [
                'date' => $myFormatForView,
                'fahrenheit' => $row['fahrenheit']
              ];
      }
      //header('Content-type:application/json;charset=utf-8');
      header("Access-Control-Allow-Origin: *");
      echo json_encode($return);

      // Close connection.
      mysqli_close($conn);
 ?>
