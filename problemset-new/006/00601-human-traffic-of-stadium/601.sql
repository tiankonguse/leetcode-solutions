# Write your MySQL query statement below
select
    A.id id,
    A.visit_date visit_date,
    A.people people
from
    Stadium A,
    Stadium B,
    Stadium C
where
    A.people >= 100
    and B.people >= 100
    and C.people >= 100
    and (
        (
            A.id = B.id - 1
            and A.id = C.id - 2
        )
        or (
            A.id = B.id - 1
            and A.id = C.id + 1
        )
        or (
            A.id = B.id + 1
            and A.id = C.id + 2
        )
    )
    group by A.id,A.visit_date,A.people
    order by A.id