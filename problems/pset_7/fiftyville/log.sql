-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- Checking the description of the crime happened at the given location and time.

SELECT name, transcript FROM interviews
WHERE year = 2021  AND month = 7  AND day = 28;
-- Two incidents happened that day. Only one is related to theft. Other is related to littering.

SELECT name, transcript  FROM interviews
WHERE year = 2021   AND month = 7   AND day = 28   AND transcript LIKE '%bakery%';

-- Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.  So, checking the transactions (and Account Owners). Adding to suspect List.
SELECT name, atm_transactions.amount FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw';

-- Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT name, phone_calls.duration FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60; -- Checking the phone call records to make a suspect list for people who might bought the tickets.

-- checking the possible names of the call-receiver
SELECT name, phone_calls.duration FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60


SELECT flights.id, full_name, city, flights.hour, flights.minute FROM airports JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29; -- Finding the flights on July 29 from Fiftyville airport, and ordering them by time.

SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id -- First flight comes out to be at 8:20 to LaGuardia Airport in New York City (Flight id- 36). This could be the place where the thief went to.
WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8 AND flights.minute = 20; -- Comparing name with Phone call to find out who bought the tickets.


-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame. So Checking the Security Logs for the license plates (And Car Owners) of cars within that time frame. Adding to suspect List.
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = 'exit' AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25





-- Bruce must the thief as he is in all the 4 tables - table of passengers , table of atm transactions, table of phone calls, and table of bakery security logs (License Plate).
--
--
--
