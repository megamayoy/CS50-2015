<?php



  // configuration
    require("../includes/config.php");

if($_SERVER["REQUEST_METHOD"] == "GET")
{
  
   render("reset_form.php");
}

else if($_SERVER["REQUEST_METHOD"] == "POST")
{

   query("UPDATE users SET hash = ? WHERE id = ?",crypt($_POST["newpass"]),$_SESSION["id"]);

      print ("RESET DONE");
}

?>
