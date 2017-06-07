<?php
  
  require("../includes/config.php");
   if($_SERVER["REQUEST_METHOD"] == "GET") 
   {
        render("quote_form.php", ["title" => "SEARCH QUOTES"]);
      
   }
 else if($_SERVER["REQUEST_METHOD"] == "POST")
 {
     $_POST["quote"] = strtoupper($_POST["quote"] );
      $result = lookup($_POST["quote"]);
     if($result === false)
     {
       apologize("not found");
     }
    else
   {  
      
      render("quote.php",$result);

   }

    
 



 } 







?>
