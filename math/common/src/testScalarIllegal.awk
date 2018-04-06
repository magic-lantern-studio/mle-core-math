BEGIN {
	first = 1;
	lastLineNo = -1;
	mustAbort = 0;
}
{
	lineNo = $3;

## Want lineNo to be a number, so check that.  If not, ignore this line.
	if (lineNo + 1 <= lineNo) {
		next;
	}

## At the first numbered error line, pretend we just saw an error on the previous line.
	if (first) {
		first = 0;
		lastLineNo = lineNo - 1;
	}

## If the line number of the error skipped a line from the previous error,
### there is a chance the compiler erroneously accepted a broken statement.
## Flag it, mark the abort variable, and continue.

	if (lineNo != (lastLineNo + 1)) {
		print "Missing compiler error on line ", lastLineNo+1, " of file ", $1;
		mustAbort = 1;
	}
	lastLineNo = lineNo;
}
END {
	if (mustAbort) {
		exit 1;
	}
	else {
		exit 0;
	}
}


