<div>
   <a href = "buy.php" role = "button" class ="btn btn-info">BUY</a>
<a href = "sell.php" role = "button" class ="btn btn-info">SELL</a>
<a href = "history.php" role = "button" class ="btn btn-info">HISTORY</a>
<a href = "quote.php" role = "button" class ="btn btn-info">SEARCH QUOTES</a>
<a href = "reset.php" role = "button" class ="btn btn-info">RESET PASSWORD</a>
     <br>
     <br>
    <table class ="table table-bordered" >
    <?php

         print("<tr>");
             print("<th> SYMBOL </th>");
             print("<th> SHARES </th>");
             print("<th> PRICE </th>"); 
             print("<th>TOTAL</th>"); 
             print("</tr>"); 
        
     
        foreach ($positions as $position)
        {
            $position["price"] = number_format($position["price"],2);
            $total = $position["shares"]*$position["price"];
             $total = number_format($total,2);

             print("<tr>");
             print("<td>{$position["symbol"]}</td>");
             print("<td>{$position["shares"]}</td>");
             print("<td>{$position["price"]}</td>");
             print("<td>$total</td>");
           
            
            print("</tr>");
        }
    

    ?>

</table>

           <?php print ("CASH: $cash"); ?>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
