# Write your MySQL query statement below
select
    T.request_at `Day`,
    ROUND(
        sum(IF(T.status = 'completed', 0, 1)) / count(T.status),
        2
    ) as `Cancellation Rate`
from
    Trips T,
    Users UC,
    Users UD
where
    T.client_id = UC.users_id
    and UC.banned = 'NO'
    and T.driver_id = UD.users_id
    and UD.banned = 'NO'
    and T.request_at >= '2013-10-01'
    and T.request_at <= '2013-10-03'
group by
    T.request_at
order by
    T.request_at