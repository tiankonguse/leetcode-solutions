
delete from Person where Id not in (select min(Id) from Person group by Email);
--- You can't specify target table 'Person' for update in FROM clause  ---




delete from Person where Id not in (select t2.Id as Id from (select min(t1.Id) as Id from Person t1 group by t1.Email) t2);

