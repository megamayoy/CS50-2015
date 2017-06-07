<?php

 // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "buy"]);
    }
   else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       if(empty($_POST["symbol"]))
       {
            apologize("you need to provide a stock to buy");
       }
      if(empty($_POST["shares"]))
       {
         apologize("you need to provide a number of stocks to buy");
       }
        
            $stock = $_POST["symbol"];
             $stock = strtoupper($stock);
         
               if(preg_match("/^\d+$/", $_POST["shares"]) == false  )
               {
                apologize("input an whole non negative integer number of shares");
               }
                
                   $symbol = lookup($stock);
         if($symbol === false )
        {
           apologize("symbol not found try again");         
        }
        
                 $price = $_POST["shares"] * $symbol["price"];
                   
                        $price = number_format($price,2);
 
       $cash = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);
                      $cash= $cash[0]["cash"];
     
                if($cash < $price )
                {
                     apologize("you don't have enough money");
                }
                 else
                {
                   
                    $cash = $cash - $price; 
                   // update information in 2 tables 
                     query("UPDATE users SET cash = ? WHERE id = ?",$cash,$_SESSION["id"] );
                
query("INSERT INTO profile (id, symbol, shares) VALUES(?,?,?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",$_SESSION["id"],$symbol["symbol"],$_POST["shares"]);
         
             $symbol["price"] = number_format($symbol["price"],2);
 query("INSERT INTO history (transaction,id,symbol,price,shares) VALUES(?,?,?,?,?)","BUY",$_SESSION["id"],$symbol["symbol"],$symbol["price"],$_POST["shares"]);         

          print("buying is done");
           

                }
    
              

     }


?>
