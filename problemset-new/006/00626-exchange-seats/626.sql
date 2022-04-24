select
    (case
        when mod(id, 2) != 0 and counts != id then id + 1
        when mod(id, 2) != 0 and counts = id then id
        else id - 1
    end)  id,
    student
from
    seat,
    (select
        COUNT(*) counts
    from
        seat)  seat_counts
order by id asc;
