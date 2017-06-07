<?php


  // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
         $_POST["symbol"] = strtoupper($_POST["symbol"]);
       if(empty($_POST["symbol"]))
       {
            apologize("you need to provide a stock to sell");
       }
      else
      {
               $row = query("SELECT symbol,shares FROM profile WHERE id = ? AND symbol = ?",$_SESSION["id"],$_POST["symbol"] );

             if($row == false)
             {
                apologize("not found try again"); 
             }
             else
             {
         
                  // get the money for selling stocks 
                  // get the number of shares
                    $shares = $row[0]["shares"];
                   // get the price per share
                  $price = lookup($_POST["symbol"]);
                    
                  $price = $price["price"];
                                     
                  $money = $shares * $price;
                   $money = number_format($money,2);
                     
                    
                // delete stock from profile
       $delete = query("DELETE FROM profile WHERE id =? AND symbol = ?",$_SESSION["id"],$_POST["symbol"]);
                  // update cash
                  
  $update = query("UPDATE users SET cash = cash + $money WHERE id = ?",$_SESSION["id"]);
                 $price = number_format($price,2);
            query("INSERT INTO history (transaction,id,symbol,shares,price) VALUES(?,?,?,?,?)","SELL",$_SESSION["id"],$_POST["symbol"],$shares,$price); 
                   
                    print("selling is done"); 
                   
             }
       
         
      }
   

    }



?>
