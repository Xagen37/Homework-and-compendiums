my $text;
while (<>)
{
    s/<([^>]*)>//g;
    unless (/^\s*$/)
    {
        s/^\s*(\S+)/$1/;
        s/(\S+)(\s*(\n{1})|\s*)$/$1$3/;
        s/(\s)\g1+/$1/g;
    }
    else 
    {
        s/^.*$/\n/;
    }
    
	$text .= $_;
}
$text =~ s/^(\s*\n)*//; 
$text =~ s/(\s*\n)*$//; 
$text =~ s/(\s*\n){2,}/\n\n/g; 
print $text;