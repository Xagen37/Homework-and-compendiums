package md2html.markup;

import java.util.List;

public class Underline extends AbstractMarkdownUnit {
    public Underline(List<MarkdownUnit> source) {
        super(source);
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<u>");
        super.toHtml(source);
        source.append("</u>");
    }
}
