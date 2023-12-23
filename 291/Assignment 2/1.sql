.print Question 1 - dchu
--uids with gold badge and question post

SELECT users.uid FROM users, ubadges, posts, badges, questions
WHERE ubadges.bname = badges.bname  AND badges.type = 'gold' AND questions.pid = posts.pid


;