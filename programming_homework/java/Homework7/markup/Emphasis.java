package markup;

import java.util.List;

public class Emphasis extends Paragraph {
    public Emphasis(List<MarkdownUnit> source) {
        super(source);
    }

    @Override
    public void toMarkdown(StringBuilder source) {
        source.append("*");
        super.toMarkdown(source);
        source.append("*");
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<em>");
        super.toHtml(source);
        source.append("</em>");
    }
}
