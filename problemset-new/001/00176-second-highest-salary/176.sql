#Write your MySQL query statement below
select
    (
        select
            distinct Salary
        from
            Employee
        order by
            Salary desc
        limit
            1 offset 1
    ) AS SecondHighestSalary;