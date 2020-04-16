package md2html.markup;

import java.util.List;

public class Code extends AbstractMarkdownUnit {
    public Code(List<MarkdownUnit> source) {
        super(source);
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<code>");
        super.toHtml(source);
        source.append("</code>");
    }
}
