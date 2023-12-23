.echo on
--question 1
--uids with gold badge and question post
SELECT ubadges.uid FROM ubadges
INNER JOIN badges ON ubadges.bname = badges.bname;