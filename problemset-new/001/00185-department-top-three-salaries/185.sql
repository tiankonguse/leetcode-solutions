select
    d1.name Department,
    e1.name Employee,
    e1.salary Salary
from
    Employee e1
    left join Department d1 on e1.departmentId = d1.id
where
    3 > (
        select
            count(distinct(e2.salary))
        from
            Employee e2
        where
            e1.departmentId = e2.departmentId
            and e1.salary < e2.salary
    );