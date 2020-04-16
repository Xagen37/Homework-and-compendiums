package md2html.markup;

import java.util.List;

public class Strikeout extends AbstractMarkdownUnit {
    public Strikeout(List<MarkdownUnit> source) {
        super(source);
    }

    @Override
    public void toMarkdown(StringBuilder source) {
        source.append("~");
        super.toMarkdown(source);
        source.append("~");
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<s>");
        super.toHtml(source);
        source.append("</s>");
    }
}
