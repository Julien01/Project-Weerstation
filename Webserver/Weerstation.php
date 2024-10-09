<?php
session_start();

require 'db.php'; // Zorg ervoor dat dit de juiste databaseverbinding instelt

// Database configuratie
define('DB_NAME', 'projectweerstation'); // De naam van je database

/* POST => Create DB action */
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    try {
        // Lees de raw POST data
        $rawData = file_get_contents("php://input");

        // Parse de data handmatig (Temp=22.5&Humidity=55&Pressure=1013&UID=Poepje)
        parse_str($rawData, $postData);

        // Verkrijg POST-gegevens uit de geparste string
        $temp = isset($postData['Temp']) ? $postData['Temp'] : null; // Temperatuur
        $humidity = isset($postData['Humidity']) ? $postData['Humidity'] : null; // Luchtvochtigheid
        $pressure = isset($postData['Pressure']) ? $postData['Pressure'] : null; // Luchtdruk
        $uid = isset($postData['UID']) ? trim($postData['UID']) : null; // Unieke identifier voor validatie

        // Alleen doorgaan als de UID overeenkomt
        if ($uid == 'Poepje') {
            // Valideer de invoer
            if ($temp === null || $humidity === null || $pressure === null) {
                throw new Exception('Temp, Humidity en Pressure waarden zijn vereist');
            }

            // Open een verbinding met de database
            $mysqli = db_open();

            // Stel de database in (selecteer de juiste database)
            $mysqli->select_db(DB_NAME);

            // Zoek het hoogste ID in de tabel "metingen"
            $result = $mysqli->query('SELECT MAX(ID) AS max_id FROM metingen');
            if ($result) {
                $row = $result->fetch_assoc();
                $new_id = isset($row['max_id']) ? $row['max_id'] + 1 : 1; // Als max_id leeg is, begin bij 1
            } else {
                throw new Exception('Fout bij het ophalen van het hoogste ID');
            }

            // Genereer de huidige tijd met PHP's date() functie
            $current_time = date('Y-m-d H:i:s'); // Formaat: Jaar-Maand-Dag Uur:Minuut:Seconde

            // Voeg de gegevens toe aan de tabel "metingen" inclusief het nieuwe ID en de huidige tijd
            $query = sprintf(
                'INSERT INTO metingen (ID, Temp, Humidity, Pressure, Tijd) VALUES ("%s", "%s", "%s", "%s", "%s")',
                $mysqli->real_escape_string($new_id),
                $mysqli->real_escape_string($temp),
                $mysqli->real_escape_string($humidity),
                $mysqli->real_escape_string($pressure),
                $mysqli->real_escape_string($current_time)
            );

            // Voer de query uit
            if ($mysqli->query($query) === TRUE) {
                http_response_code(200); // status ok
                echo "Data succesvol ingevoerd: ID = $new_id, Temp = $temp, Humidity = $humidity, Pressure = $pressure, Tijd = $current_time\n"; // Bevestiging met de ingevoerde waarden
            } else {
                // Print fout als de query mislukt
                http_response_code(400); // Bad request
                echo "Fout bij het invoeren van gegevens in de tabel 'metingen': " . $mysqli->error; // Foutmelding
            }
        } else {
            http_response_code(401); // Unauthorized
            echo "Ongeldige UID\n"; // Toon de foutmelding bij een ongeldige UID
        }
    } catch (Exception $e) {
        http_response_code(400); // Bad request
        echo "Fout: " . $e->getMessage() . "\n"; // Algemene foutmelding
    }
}
?>