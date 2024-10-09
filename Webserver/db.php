<?php
function db_open() {
    $host = 'localhost'; // Database host
    $user = 'root';      // Database username (default for XAMPP)
    $password = '';      // Database password (default is empty for XAMPP)
    $database = 'projectweerstation'; // Your database name

    // Create connection
    $mysqli = new mysqli($host, $user, $password, $database);

    // Check connection
    if ($mysqli->connect_error) {
        die('Connect Error (' . $mysqli->connect_errno . ') ' . $mysqli->connect_error);
    }

    return $mysqli;
}
?>
