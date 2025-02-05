-- write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
SELECT DISTINCT name FROM movies, people, stars WHERE movies.id = stars.movie_id AND people.id = stars.person_id AND year = 2004 ORDER BY birth;
