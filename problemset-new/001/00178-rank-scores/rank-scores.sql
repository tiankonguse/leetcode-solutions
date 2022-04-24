# Write your MySQL query statement below
select t4.score score, t3.Rank `rank` from Scores t4, (select  t1.score as score, count(*) as `Rank` from (select score from Scores group by score) t1 left join (select score from Scores group by score) t2 on t1.score <= t2.score group by t1.score) t3 where t4.score = t3.score order by t3.Rank, t4.score;


