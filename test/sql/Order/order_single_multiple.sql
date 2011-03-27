echo SELECT * FROM t1 WHERE f1 <= 4 ORDER BY f1;
SELECT * FROM t1 WHERE f1 <= 4 ORDER BY f1;
echo SELECT * FROM t1 WHERE f1 <= 4 ORDER BY f1 DESC;
SELECT * FROM t1 WHERE f1 <= 4 ORDER BY f1 DESC;
echo SELECT f1, t1.f2, f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY t1.f1, f4;
SELECT f1, t1.f2, f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY t1.f1, f4;
echo SELECT f1, f2, t1.f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1, t1.f4 DESC;
SELECT f1, f2, t1.f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1, t1.f4 DESC;
echo SELECT f1, f2, t1.f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1 DESC, t1.f4 DESC;
SELECT f1, f2, t1.f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1 DESC, t1.f4 DESC;
echo SELECT f1, t1.f4, f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY t1.f1, f4, t1.f2;
SELECT f1, t1.f4, f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY t1.f1, f4, t1.f2;
echo SELECT t1.f1, f4, t1.f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1, t1.f4, f2 DESC;
SELECT t1.f1, f4, t1.f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1, t1.f4, f2 DESC;
echo SELECT t1.f1, f4, t1.f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1 DESC, t1.f4 DESC, f2 DESC;
SELECT t1.f1, f4, t1.f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1 DESC, t1.f4 DESC, f2 DESC;