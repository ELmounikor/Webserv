<!DOCTYPE html>
<html>
<head>
    <title>Name and Age</title>
</head>
<body>
    <form action="" method="POST">
        <label for="name">Name:</label>
        <input type="text" name="name" id="name" required><br><br>

        <label for="age">Age:</label>
        <input type="number" name="age" id="age" required><br><br>

        <input type="submit" value="Submit">
    </form>

    <?php
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        // Check if the form has been submitted
        if (isset($_POST['name']) && isset($_POST['age'])) {
            // Retrieve the submitted name and age
            $name = $_POST['name'];
            $age = $_POST['age'];

            // Display the output
            echo '<p style="color: green;">The age of ' . $name .  ' is: ' . $age . '</p>';
        }
    }
    ?>
</body>
</html>