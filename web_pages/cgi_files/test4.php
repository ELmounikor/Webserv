<?php
// Check if the 'name' parameter is provided via GET
if (isset($_GET['name'])) {
    // Retrieve the value of the 'name' parameter
    $name = $_GET['name'];

    // Display a greeting with the provided name
    echo "Hello, " . $name . "!";
} else {
    // 'name' parameter is not provided, display a generic message
    echo "Please provide a name via the 'name' parameter.";
}
?>