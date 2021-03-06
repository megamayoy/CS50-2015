


<?php

    // configuration
    require("../includes/config.php"); 

    $rows = query("SELECT symbol,shares FROM profile WHERE id = ?",$_SESSION["id"]);


   $positions = [];
foreach ($rows as $row)
{
    $stock = lookup($row["symbol"]);
    if ($stock !== false)
    {
        $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
        ];
    }
}
  $money = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);

  $cash = $money[0]["cash"];
  $cash = number_format($cash,2);
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio","positions"=>$positions, "cash"=> $cash ]);

?>

