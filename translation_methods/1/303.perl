my %texts;

while ($input = <>)
{
    if($input =~ /<\s*a.+\bhref\s*=\s*"(?<str>.+?)".*?>/g)
    {
        my $val = $+{str};
        #print $val;
        #print "\n";
        $val =~ /([^:\/\?#\.]+:)?(\/\/)?(?<link>[^\/\?#:]+)(:\d+)?([\/:#\?].*)?/;
        $val = $+{link};
        if ($val !~ /^[\s\.]*$/)
        {
            $texts{$val} = 1;
            #push @texts, $+{link};
        }
    }
}

for $text (sort keys %texts)
{
    print $text;
    print "\n";
}