select A.name name, ifnull(B.s, 0) travelled_distance
from Users A left Join (select user_id,sum(distance) s from Rides group by user_id) B on A.id = B.user_id
order by travelled_distance desc,name