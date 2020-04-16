package md2html.markup;

import java.util.List;

public class Header extends AbstractMarkdownUnit{
    private int rank;

    public Header(List<MarkdownUnit> source, int rank) {
        super(source);
        this.rank = rank;
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<h" + rank + ">");
        super.toHtml(source);
        source.append("</h" + rank + ">");
    }
}
