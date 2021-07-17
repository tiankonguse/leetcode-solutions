CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT BEGIN RETURN (
    # Write your MySQL query statement below.
    select
        t1.Salary SecondHighestSalary
    from
        (
            select
                distinct(Salary) as Salary
            from
                Employee
        ) t1
        left join (
            select
                distinct(Salary) as Salary
            from
                Employee
        ) t2 on t1.Salary <= t2.Salary
    group by
        t1.Salary
    having
        count(t2.Salary) = N
);

END