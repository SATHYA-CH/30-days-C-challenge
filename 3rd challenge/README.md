Start
read amount, cstype (customer type), and dist (distance in km).
If cstype = 1: discount = 15% when amount ≥ 2000, otherwise 10%.
If cstype = 2: discount = 8% when amount ≥ 3000, otherwise 0%.
Set delivery charges: 40 if dist ≤ 5, 70 if dist is 6 to 15, 100 if dist > 15.
Calculate discount amount ds = amount × discount / 100, then disamt = amount - ds.
Calculate finalamount = disamt + dcharges.
Print the purchase amount, discount, amount after discount, delivery charges, and final payable amount.
Stop.
