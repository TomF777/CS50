-- write a SQL query that returns the average energy of songs that are by Drake
SELECT AVG(energy) from songs WHERE artist_id = (select id from artists WHERE name = 'Drake');
