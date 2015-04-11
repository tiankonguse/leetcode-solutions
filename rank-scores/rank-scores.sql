# Write your MySQL query statement below
select t4.Score, t3.Rank from Scores t4, (select  t1.Score as Score, count(*) as Rank from (select Score from Scores group by Score) t1 left join (select Score from Scores group by Score) t2 on t1.Score <= t2.Score group by t1.Score) t3 where t4.Score = t3.Score order by t3.Rank, t4.Score;


