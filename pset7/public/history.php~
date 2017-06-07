
<?php 


// configuration
    require("../includes/config.php"); 


$rows = query("SELECT* FROM history WHERE id = ?",$_SESSION["id"] ); 

if($rows == false)
{
   apologize("there's no history"); 
}

   render("history.php",["title" => "history","rows" => $rows]);
     
?>



