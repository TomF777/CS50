-- write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT DISTINCT title  from people, stars, movies, ratings
WHERE people.id = stars.person_id AND
movies.id = stars.movie_id AND
ratings.movie_id = movies.id AND
name = "Chadwick Boseman"
ORDER BY rating DESC LIMIT 5;
