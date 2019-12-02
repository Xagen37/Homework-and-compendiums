package md2html.markup;

import java.util.ArrayList;
import java.util.List;

public class Paragraph extends AbstractMarkdownUnit{
    public Paragraph(List<MarkdownUnit> source) {
        super(source);
    }

    @Override
    public void toMarkdown(StringBuilder source) {
        super.toMarkdown(source);
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<p>");
        super.toHtml(source);
        source.append("</p>");
    }
}
