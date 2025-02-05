-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Input data:
--  Theft took place on July 28
--  Theft took place on Humphrey Street

-- Finding crime details --
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28 AND description LIKE "%CS50%";       -> 3 witnesses , bakery at 10.15
-- it gives us information there were three witnesses and theft took place at 10.15 at Humphrey Street bakery

-- investigating interviews
SELECT * from interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- result:
--Ruth: <Sometime within ten minutes> of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

--Eugene: I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on <Leggett Street> and saw the thief there <withdrawing> some money.

--Raymond: As the thief was leaving the bakery, they <called someone> who talked to them for <less than a minute>.
--In the call, I heard the thief say that they were planning to take the <earliest flight> <out of Fiftyville tomorrow>.
--The thief then asked the person on the other end of the phone to <purchase the flight ticket>.


-- Now a bigger query to evaluate the sentences from the witnesses:
-- 1st part of the query checks the information from Ruth:
-- It checks person's licence plate of leaving cars (activity=exit) from bakery between 10.15 and 10.25 ("within 10 minutes")

--2nd part of query checks information form Eugene:
-- It finds people id who did withdraw money at the ATM at Leggett Street on the day of theft.

--3rd part of the query checks information from Raymond:
-- It finds persons from call register, whom call duration was less then a minute (60 seconds)
SELECT *
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
         FROM bakery_security_logs
         WHERE activity = "exit" AND month=7 AND day=28 AND hour=10 AND minute >=15 AND minute<=25
        )
    AND id IN
    (SELECT person_id
     FROM bank_accounts
     WHERE account_number IN
        (SELECT account_number
         FROM atm_transactions
         WHERE month = 7 AND day = 28 AND transaction_type="withdraw" AND atm_location="Leggett Street"
        )
    )
     AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60);

--This results in theft suspects:
--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--+--------+-------+----------------+-----------------+---------------+

--Next we check the receiver (potential accomplices) of the above callers:
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls
WHERE month=7 AND day=28 AND duration<60 and caller IN ("(770) 555-1861", "(367) 555-5533"));
--+--------+--------+----------------+-----------------+---------------+
--|   id   |  name  |  phone_number  | passport_number | license_plate |
--+--------+--------+----------------+-----------------+---------------+
--| 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
--| 864400 | Robin  | (375) 555-8161 | NULL            | 4V16VO0       |
--+--------+--------+----------------+-----------------+---------------+


--Next it checks the information from Raymond about the planned flight:
--It finds the earliest flight on next day after theft i.e. 29 of July from Fiftyville:
SELECT id, hour, minute, origin_airport_id, destination_airport_id
FROM flights
WHERE month=7 AND day=29 AND origin_airport_id =
(SELECT id FROM airports WHERE city="Fiftyville")
ORDER BY hour ASC LIMIT 1;
The result:
--+----+------+--------+-------------------+------------------------+
--| id | hour | minute | origin_airport_id | destination_airport_id |
--+----+------+--------+-------------------+------------------------+
--| 36 | 8    | 20     | 8                 | 4                      |
--+----+------+--------+-------------------+------------------------+
--We notice the flight id is = 36.



--Based on the output we see that id destination airport is 4 which corresponds to New York City:
SELECT * FROM airports;
--+----+--------------+-----------------------------------------+---------------+
--| id | abbreviation |                full_name                |     city      |
--+----+--------------+-----------------------------------------+---------------+
--| 1  | ORD          | O'Hare International Airport            | Chicago       |
--| 2  | PEK          | Beijing Capital International Airport   | Beijing       |
--| 3  | LAX          | Los Angeles International Airport       | Los Angeles   |
--| 4  | LGA          | LaGuardia Airport                       | New York City |
--| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
--| 6  | BOS          | Logan International Airport             | Boston        |
--| 7  | DXB          | Dubai International Airport             | Dubai         |
--| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
--| 9  | HND          | Tokyo International Airport             | Tokyo         |
--| 10 | CDG          | Charles de Gaulle Airport               | Paris         |
--| 11 | SFO          | San Francisco International Airport     | San Francisco |
--| 12 | DEL          | Indira Gandhi International Airport     | Delhi         |
--+----+--------------+-----------------------------------------+---------------+

SELECT city FROM airports WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE month=7 AND day=29 AND origin_airport_id =
    (SELECT id FROM airports WHERE city="Fiftyville")
    ORDER BY hour ASC LIMIT 1
);
--+---------------+
--|     city      |
--+---------------+
--| New York City |
--+---------------+
-- So now we know that the city the thief ESCAPED TO is New York CITY


--We know from previous queries that flight id=36 and potential thiefs are Bruce or Diana
--We check passengers in flight 36 which name is Bruce or Diana.
--We join people, passengers, flights tables
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 36 AND name IN ("Bruce", "Diana")
ORDER BY hour ASC;

--This gives us the thief name:
--+-------+
--| name  |
--+-------+
--| Bruce |
--+-------+


-- Next we check the call register for receiver of Bruce call. Call < 60 sec on the day of theft
SELECT name
FROM people
WHERE phone_number =
    (SELECT receiver
     FROM phone_calls
     WHERE month = 7 AND day = 28 AND duration < 60 AND caller =
        (SELECT phone_number
         FROM people
         WHERE name = "Bruce"));

--+-------+
--| name  |
--+-------+
--| Robin |
--+-------+
-- It gives the result that the accomplice is Robin
