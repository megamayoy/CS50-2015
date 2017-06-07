     <div>
       <table class ="table table-bordered" >
         <?php


             print("<tr>");
             print("<th> TRANSACTION </th>");
             print("<th> date/time </th>");
             print("<th> SYMBOL </th>");
             print("<th> SHARES </th>");
             print("<th> PRICE PER SHARE </th>"); 
             print("</tr>"); 

         foreach ($rows as $position)
        {
          $position["price"] = number_format($position["price"],2);
             print("<tr>");
             print("<td>{$position["transaction"]}</td>");
             print("<td>{$position["date/time"]}</td>");
             print("<td>{$position["symbol"]}</td>");
             print("<td>{$position["shares"]}</td>");
             print("<td>{$position["price"]}</td>");
            
           
            
            print("</tr>");
        }
    
?>
</table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>

